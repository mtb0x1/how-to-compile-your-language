#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

#include "codegen.h"
#include "lexer.h"
#include "parser.h"
#include "sema.h"

void displayHelp() {
  std::cout << "Usage:\n"
            << "  your-compiler [options] <source_file>\n\n"
            << "Options:\n"
            << "  -h           display this message\n"
            << "  -o <file>    write executable to <file>\n";
}

void error(std::string_view msg) {
  std::cerr << "error: " << msg << '\n';
  std::exit(1);
}

struct CompilerOptions {
  std::optional<std::string_view> source;
  std::optional<std::string_view> output;
  bool displayHelp = false;
};

CompilerOptions parseArguments(int argc, const char **argv) {
  CompilerOptions options{std::nullopt, std::nullopt, false};

  int idx = 1;
  while (idx < argc) {
    std::string_view arg{argv[idx]};

    if (arg[0] != '-') {
      if (options.source)
        error("unexpected argument '" + std::string{arg} + '\'');

      options.source = arg;
    } else {
      if (arg == "-h")
        options.displayHelp = true;
      else if (arg == "-o")
        options.output = ++idx >= argc ? "" : argv[idx];
      else
        error("unexpected option '" + std::string{arg} + '\'');
    }

    ++idx;
  }

  return options;
}

int main(int argc, const char **argv) {
  CompilerOptions options = parseArguments(argc, argv);

  if (options.displayHelp) {
    displayHelp();
    return 0;
  }

  if (!options.source)
    error("no source file specified");

  std::ifstream file{options.source->data()};
  if (!file)
    error("failed to open '" + std::string{*options.source} + '\'');

  std::stringstream buffer;
  buffer << file.rdbuf();
  SourceFile sourceFile{*options.source, buffer.str()};

  TheLexer lexer{sourceFile};
  TheParser parser{lexer};
  Sema sema{parser.parseSourceFile()};
  Codegen codegen{sema.resolveSourceFile()};

  std::string_view outLL = "tmp.ll";
  codegen.generateIR(outLL);

  std::stringstream command;
  command << "clang " << outLL << " -Wno-override-module";
  if (options.output)
    command << " -o " << *options.output;

  std::system(command.str().c_str());
  std::filesystem::remove(outLL);

  return 0;
}
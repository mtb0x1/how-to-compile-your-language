file(GLOB compiler_src CONFIGURE_DEPENDS "*.cpp")

add_executable(compiler ${compiler_src})

llvm_map_components_to_libnames(llvm_libs support core irreader)

target_link_libraries(compiler ${llvm_libs})

# Add include directories for the target
target_include_directories(compiler PRIVATE ${LLVM_INCLUDE_DIRS})

# Add compile definitions for the target to ensure dump is enabled
target_compile_definitions(compiler PRIVATE LLVM_ENABLE_DUMP)
// RUN: compiler %s 2>&1 | filecheck %s
fn main(): void {
    1.0
// CHECK: [[# @LINE + 1 ]]:1: error: expected ';' at the end of statement
}

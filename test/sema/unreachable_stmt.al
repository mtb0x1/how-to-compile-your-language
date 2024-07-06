// RUN: (compiler %s || true) 2>&1 | filecheck %s
fn singleReturn(): void {
    return;
}

fn multipleReturns(): void {
    1.0;
    return;

    // CHECK: [[# @LINE + 1 ]]:5: warning: unreachable statement
    2.0;
    return;
    
    3.0;
    return;
}

fn multipleReturnsAfterEachOther(): void {
    return;
    // CHECK: [[# @LINE + 1 ]]:5: warning: unreachable statement
    return;
}

fn branch(x: number): void {
    if 1.0 || x {
        1.0;
        return;
        // CHECK: [[# @LINE + 1 ]]:9: warning: unreachable statement
        2.0;
    }

    return;
    // CHECK: [[# @LINE + 1 ]]:5: warning: unreachable statement
    3.0 + 5.0;
}

fn loop(x: number): void {
    while x {
        return;
        // CHECK: [[# @LINE + 1 ]]:9: warning: unreachable statement
        1.0;
    }
}

fn main(): void {}

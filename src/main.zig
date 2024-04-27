const std = @import("std");
const brainfuck = @import("brainfuck.zig").Brainfuck;

pub fn main() !void {
    const allocator = std.heap.page_allocator;
    var bf = try brainfuck.init(30_000, allocator);
    defer bf.deinit(allocator);

    //const sixty_five = ">++++++++[<++++++++>-]<+.";
    //try bf.executeString(sixty_five);
    //const hello_world = "++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+++++++..+++.>++.<<+++++++++++++++.>.+++.------.--------.>+.>.";
    //try bf.executeString(hello_world);

    try bf.executeFile("./tests/helloworld.bf");
}

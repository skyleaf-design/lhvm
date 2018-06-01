// Import node_wrapper.cpp, which contains liblhvm.c
const lhvm = require('./build/Release/lhvm');

// Using the wrapper, pass liblhvm some NumberForth strings, inspect the
// results, and then pass or fail the tests depending on the result.
// console.log(addon.hello());
// console.log(addon.string());
// console.log(addon.echo("not true"));
// console.log(addon.echo(true));
//lhvm()({ test: 123 });
console.log(lhvm.get_type("testing"));
console.log(lhvm.get_type({ is_an_object: true }));
console.log(lhvm.get_type(true));
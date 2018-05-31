// Import node_wrapper.cpp, which contains liblhvm.c
const addon = require('./build/Release/lhvm.node');

// Using the wrapper, pass liblhvm some NumberForth strings, inspect the
// results, and then pass or fail the tests depending on the result.
console.log(addon.hello());
console.log(addon.string());
console.log(addon.echo("not true"));
console.log(addon.echo(true));
const gulp = require('gulp4');
const exec = require('child_process').exec;
const log = require('fancy-log');

const clang_build = "clang src/main.c -o dist/liblhvm";
const gyp_build = "node-gyp build";

function build(done) {
  exec(clang_build, function (error, stdout, stderr) {
    log("Compiled.");
    if (stdout.length > 0) log(stdout);
    if (stderr.length > 0) log(stderr);
    done();
  });
}

function gyp(done) {
  exec(gyp_build, function (error, stdout, stderr) {
    log("Built the Node addon.");
    if (stdout.length > 0) log(stdout);
    if (stderr.length > 0) log(stderr);
    done();
  });
}

function watch(done) {
  gulp.watch('src/*.c', build);
  gulp.watch('node_wrapper.cpp', gyp);
  done();
};

gulp.task('default', gulp.series([ build, gyp, watch ]));
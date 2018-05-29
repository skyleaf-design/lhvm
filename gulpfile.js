const gulp = require('gulp4');
const exec = require('child_process').exec;
const log = require('fancy-log');

const clang_build = "clang src/main.c -o dist/liblhvm";

function build(done) {
  exec(clang_build, function (error, stdout, stderr) {
    log("Compiled.");
    if (stdout.length > 0) log(stdout);
    if (stderr.length > 0) log(stderr);
    done();
  });
}

function watch() {
  return gulp.watch('src/*.c', build);
};

gulp.task('default', gulp.series([ build, watch ]));
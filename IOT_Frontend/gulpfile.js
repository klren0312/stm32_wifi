var gulp = require('gulp');
var concat = require('gulp-concat');
var browserSync = require('browser-sync').create();
var uglifyjs = require("uglify-js");
var minifycss = require('gulp-minify-css');

// 将task集合在一起 使用gulp命令即可运行
gulp.task('default', ['browserSync', 'watch'])

// 浏览器同步插件初始化
gulp.task('browserSync', function() {
    browserSync.init({
        // 路径
        server: {
            baseDir: './'
        },
        port: 3010
    })
})

//打包css
gulp.task('minifycss', function() {
    return gulp.src('resources/mystyle/mycss/*.css')
        .pipe(concat('main.css'))
        .pipe(minifycss())
        .pipe(gulp.dest('resources/mystyle/'))
})

// 打包控制器
gulp.task('otherpage', function() {
    gulp.src('js/otherpage/*.js')
        .pipe(concat('controller.js'))
        .pipe(gulp.dest('js/otherpage/'))
})


// 监听js,css,html的变化，而重新加载浏览器
gulp.task('watch', function() {
    gulp.watch('js/otherpage/*.js', ['otherpage']);
    gulp.watch(['js/otherpage/*.js', 'js/myjs/*.js', 'js/*.js'], browserSync.reload);
    gulp.watch(['css/mycss/*.css'], browserSync.reload);
    gulp.watch(['*.html', 'apiTestComponent/*.html'], browserSync.reload);
})
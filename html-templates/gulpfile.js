const {src, dest, series} = require('gulp');
const parcel = require('gulp-parcel');
const htmlnano = require('gulp-htmlnano');
const del = require('del');
const postcss = require('gulp-postcss');

function bundle() {
    return src('./src/**/*.html', {read: false})
        .pipe(parcel({
            outDir: './.tmp',
            publicURL: './',
            cache: false,
            sourceMaps: false,
            scopeHoist: true,
            minify: true,
            hrm:false
        }, {source: 'build'}))
}

function build() {
    return src('./.tmp/*.html')
        .pipe(postcss())

        .pipe(dest('./dist'))
}

function clean() {
    return del(['./dist/*', '!./dist/*.html', '.tmp']);
}

exports.default = series(bundle, build, clean);

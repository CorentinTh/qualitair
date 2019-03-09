const {src, dest}   = require('gulp');
const rename        = require('gulp-rename');
const replace       = require('gulp-replace');
const inlineSource  = require('gulp-inline-source');

const jsonPlaceholder = "$JSONPLACEHOLDER$";
const datePlaceholder = "$DATEPLACEHOLDER$";

const build = () => {
    return src('./src/**/*.html')
        .pipe(inlineSource({
            compress: true
        }))
        .pipe(replace(/const\sjsonInput\s?=\s?(.*?);/ms, (match, p1) => {
            return match.replace(p1, `\`\n${jsonPlaceholder}\n\``);
        }))
        .pipe(replace(/const\sreportDate\s?=\s?(.*?);/ms, (match, p1) => {
            return match.replace(p1, `\`\n${datePlaceholder}\n\``);
        }))
        .pipe(rename({
            dirname: '.'
        }))
        .pipe(dest('./dist'))
};

exports.build = build;
exports.default = build;

#!/usr/bin/env node

const path = require('path');
const fs = require('fs');
const crypto = require('crypto');

const key = process.env['MAGICLEAP'];

if (key) {
  fs.createReadStream(path.join(__dirname, 'lib.zip.enc'))
    .pipe(crypto.createDecipher('aes-256-cbc', new Buffer(key, 'base64')))
    .pipe(fs.createWriteStream(path.join(__dirname, 'lib.zip')));
}

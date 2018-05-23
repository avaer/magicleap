#!/usr/bin/env node

const path = require('path');
const fs = require('fs');
const crypto = require('crypto');

const key = process.env['MAGICLEAP'];

if (key) {
  console.warn('Decrypting magicleap module with MAGICLEAP environment variable');
  const ws = fs.createReadStream(path.join(__dirname, 'lib.zip.enc'))
    .pipe(crypto.createDecipher('aes-256-cbc', Buffer.from(key, 'base64')))
    .pipe(fs.createWriteStream(path.join(__dirname, 'lib.zip')));
  ws.on('close', () => {
    process.exit(0);
  });
  ws.on('error', err => {
    console.warn(err.stack);
    process.exit(1);
  });
} else {
  console.warn('NOT decrypting magicleap module because MAGICLEAP environment variable not defined');
  process.exit(1);
}

#!/usr/bin/env node

const path = require('path');
const fs = require('fs');
const unzpr = require('unzpr');

const p = path.join(__dirname, 'lib.zip');
fs.lstat(p, err => {
  if (!err) {
    const ws = fs.createReadStream(p)
      .pipe(unzpr.Extract({
        path: __dirname,
      }));
    ws.on('done', () => {
      process.exit(0);
    });
    ws.on('error', err => {
      console.warn(err);
      process.exit(1);
    });
  } else if (err.code === 'ENOENT') {
    // nothing
  } else {
    throw err;
  }
});

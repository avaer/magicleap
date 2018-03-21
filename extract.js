const path = require('path');
const fs = require('fs');
const unzipper = require('unzipper');

const p = path.join(__dirname, 'lib.zip');
fs.lstat(p, err => {
  if (!err) {
    const ws = fs.createReadStream(p)
      .pipe(unzipper.Extract({
        path: __dirname,
      }));
    ws.on('close', () => {
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

const path = require('path');
const fs = require('fs');
const unzip = require('unzip');

const p = path.join(__dirname, 'lib.zip');
fs.lstat(p, err => {
  if (!err) {
    const ws = fs.createReadStream(p)
      .pipe(unzip.Extract({
        path: __dirname,
      }));
  } else if (err.code === 'ENOENT') {
    // nothing
  } else {
    throw err;
  }
});

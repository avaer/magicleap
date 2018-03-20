const path = require('path');
const fs = require('fs');
const unzip = require('unzip');
const ws = fs.createReadStream(path.join(__dirname, 'lib.zip'))
  .pipe(unzip.Extract({
    path: __dirname,
  }));

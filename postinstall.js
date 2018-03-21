#!/usr/bin/env node

const path = require('path');
const child_process = require('child_process');

const extractResult = child_process.spawnSync(process.argv[0], [
  path.join(__dirname, 'decrypt.js')
], {
  stdio: 'inherit',
});
if (extractResult.status === 0) {
  child_process.spawnSync(process.argv[0], [
    path.join(__dirname, 'extract.js')
  ], {
    stdio: 'inherit',
  });
}

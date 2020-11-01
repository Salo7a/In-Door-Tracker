const {spawn} = require('child_process');
const python = spawn('python', ['localize.py', 'model.joblib', '-76.', '-58.', '-88.', '-86.', '-87.1', '-89.', '-87.', '-74.', '-76.6'])
let location ;

// Event waiting for python console to print location 
python.stdout.on('data', function (data) {
    console.log('Pipe data from python script ...');
    location = parseInt(data.toString()[1]);
    console.log("the location is", location);
   });



// python.on('close', (code) => {
// console.log(`child process close all stdio with code ${code}`);
// // send data to browser
// res.send(dataToSend)
// });
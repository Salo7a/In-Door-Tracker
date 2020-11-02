const express = require('express')

let location ;



const app = express()
const port = 3000
app.get('/', async (req, res) => {
    const {spawn} = require('child_process');
    const python = await spawn('python', ['localize.py', 'model.joblib', '-76.', '-58.', '-88.', '-86.', '-87.1', '-89.', '-87.', '-74.', '-76.6']);
    console.log("get request done");
    // // Event waiting for python console to print location 
    // python.stdout.on('data', function (data) {
    //     console.log('Pipe data from python script ...');
    //     location = parseInt(data.toString()[1]);
    //     console.log("the location is", location);
    // });
    // Event waiting for python console to print location 
    await python.stdout.on('data', function (data) {
        console.log('Pipe data from python script ...');
        location = parseInt(data.toString()[1]);
        console.log("the location is", location);
    });
    res.send(200)
 
})
app.listen(port, () => console.log(`Example app listening on port 
${port}!`))
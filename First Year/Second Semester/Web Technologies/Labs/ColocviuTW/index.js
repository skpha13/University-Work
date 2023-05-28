const express = require('express');
const bodyParser = require('body-parser');
const path = require('path');
const app = express();
const port = 3000;

app.use(bodyParser.urlencoded({ extended: true }));
app.use(bodyParser.json());
app.use(express.static(path.join(__dirname, "")));

app.get('/', (req, res) => {
    res.sendFile(path.join(__dirname, './p4.html'));
});

app.post('/form'),(req,res) => {
    const text = req.body;  
}

app.listen(port);
console.log(`Started on: ${port}`);
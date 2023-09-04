const express = require('express');
const bodyParser = require('body-parser');
const fs = require('fs');
const app = express();

app.use(bodyParser.json());
app.use(express.static(__dirname));

app.get('/', (req, res) => {
    res.sendFile(__dirname + '/html/p3.html');
});

var persoane = [];
fs.readFile('persoane.json', (err, data) => {
    persoane = JSON.parse(data);
});

var persoaneFiltrate = [];

app.post('/', (req, res) => {
    const { cuvant, option } = req.body;
    var hasBeenFound = false;

    for (items of persoane) {
        console.log(items);
        if (items[option].toLowerCase() === cuvant.toLowerCase()) {
            if (option === 'nume') persoaneFiltrate.push(items.prenume);
            else persoaneFiltrate.push(items.nume);
            hasBeenFound = true;
        }
    }

    if (!hasBeenFound) res.send({ rezultat: `<html><body><p>NU exista</p></body></html>` });
    else {
        const temp = persoaneFiltrate.join(' ');
        res.send({ rezultat: `<html><body><p>${temp}</p></body></html>` });
    }
});

app.listen(3000, () => console.log('running...'));
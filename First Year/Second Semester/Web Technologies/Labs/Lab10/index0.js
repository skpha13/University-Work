const express = require('express');
const bodyParser = require('body-parser');
const app = express();

app.use(bodyParser.json());
app.use(express.static(__dirname));

app.get(['/abc', '/xyz'], (req, res) => {
    const messages = ['Mesajul 1',
        'Mesajul 2',
        'Mesajul 3',
        'Mesajul 4',
        'Mesajul 5',];

    res.send(messages[Math.floor(Math.random() * messages.length)]);
});

app.listen(3000, () => console.log('Running'));
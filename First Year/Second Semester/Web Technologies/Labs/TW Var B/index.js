const express = require('express');
const bodyParser = require('body-parser');
const app = express();

app.use(bodyParser.json());
app.use(express.static(__dirname));

const pattern = /^(\d+;)*\d+$/;

app.get('/', (req, res) => {
    res.sendFile(__dirname + "/p4.html");
})

app.post('/form', (req, res) => {
    const numbers = req.body.numbers;
    const order = req.body.order;

    if (!pattern.test(numbers)) {
        res.json({ "rezultat": "Invalid" });
    }
    else {
        const arr = numbers.split(';').map(Number);

        if (order === 'asc') {
            arr.sort((a, b) => a - b);
        }
        else if (order === 'desc') {
            arr.sort((a, b) => b - a);
        }

        res.json({ "rezultat": arr });
    }
});

app.listen(3000, () => console.log('Serverul rulează pe portul 3000'));
const express = require('express');
const bodyParser = require('body-parser');
const app = express();

app.use(bodyParser.json());
app.use(express.static(__dirname));

app.get('/', (req, res) => {
    res.sendFile(__dirname + '/html/p1.html');
})

app.post('/form', (req, res) => {
    const { nume, nota1, nota2 } = req.body;
    const medie = (nota1 + nota2) / 2;

    const responseText = `Studentul ${nume} are media ${medie}`;

    res.send({ 'rezultat': `<html><body>${responseText}</html></body>` });
});

app.listen(3000, () => console.log('running...'));
const express = require('express');
const bodyParser = require('body-parser');
const app = express();

app.use(bodyParser.json());
app.use(express.static(__dirname));

app.get('/', (req, res) => {
    res.sendFile(__dirname + '/html/p2.html');
});

const dictionar = [{ cuvant: "carte", engleza: "book", franceza: "livre" },
{ cuvant: "floare", engleza: "flower", franceza: "fleur" },
{ cuvant: "tablou", engleza: "picture", franceza: "photo" },
{ cuvant: "film", engleza: "movie", franceza: "film" }];

app.post('/', (req, res) => {
    const { cuvant, option } = req.body;
    var hasBeenFound = false;

    for (d of dictionar) {
        if (d.cuvant === cuvant) {
            res.send({ 'rezultat': `<html><body>${d[option]}</html></body>` });
            hasBeenFound = true;
        }
    }

    if (!hasBeenFound) res.send({ 'rezultat': `<html><body>Nu exista</html></body>` });
});

app.listen(3000, () => console.log('running...'));
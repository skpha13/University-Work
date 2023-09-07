const express = require('express');
const bodyParser = require('body-parser');
const app = express();

app.use(bodyParser.json());
app.use(express.static(__dirname));

app.get('/', (req, res) => {
    res.sendFile(__dirname + '/p4.html');
});

const ob = [{ nume: 'a', culoare: 'rosu', dimensiune: 3 },
{ nume: 'b', culoare: 'verde', dimensiune: 1 },
{ nume: 'c', culoare: 'albastru', dimensiune: 4 },
{ nume: 'd', culoare: 'verde', dimensiune: 1 },
{ nume: 'e', culoare: 'rosu', dimensiune: 5 },
{ nume: 'f', culoare: 'albastru', dimensiune: 2 },
{ nume: 'g', culoare: 'rosu', dimensiune: 1 }]

app.post('/', (req, res) => {
    let nr = 0;

    const { option, range } = req.body;

    for (let i = 0; i < ob.length; i++) {
        if (ob[i].culoare === option && ob[i].dimensiune <= range)
            nr++;
    }

    if (nr === 0) {
        res.send({ result: 'Nu exista obiecte' });
    }
    else {
        res.send({ result: nr });
    }
});

app.listen(3000, () => console.log('running...'));
const express = require('express');
const bodyParser = require('body-parser');
const app = express();

app.use(bodyParser.json());
app.use(express.static(__dirname));

app.get('/', (req, res) => {
    res.sendFile(__dirname + '/p4.html');
});

let persoane = [
    { nume: "Ion", sex: "m", varsta: 3 },
    { nume: "Oana", sex: "f", varsta: 23 },
    { nume: "Daria", sex: "f", varsta: 10 },
    { nume: "Mihai", sex: "m", varsta: 19 },
    { nume: "Gabriel", sex: "m", varsta: 22 },
    { nume: "Simona", sex: "f", varsta: 11 },
    { nume: "Bogdan", sex: "m", varsta: 28 }
];

app.post('/verifica', (req, res) => {
    const nume = req.body.nume;
    const persoana = persoane.find(p => p.nume === nume);

    if (!persoana) {
        return res.json({ rezultat: 'Nu exista numele cautat' });
    }

    let sex = persoana.sex === 'm' ? 'băiat' : 'fată';
    let minor = persoana.varsta < 18 ? 'este minor' : 'nu este minor';

    return res.json({ "rezultat": `${sex},${minor}` });
});

app.listen(3000, () => console.log('Serverul rulează pe portul 3000'));
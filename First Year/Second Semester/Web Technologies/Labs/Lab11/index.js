const express = require('express');
const formidable = require('formidable');
const fs = require('fs');
const path = require('path');

const app = express();
app.use(express.static(__dirname));

app.get('/', (req, res) => {
    res.sendFile(__dirname + '/html/comanda.html');
});

app.set('view engine', 'ejs');

app.get('/comenzi', (req, res) => {
    let raw = fs.readFileSync('produse.json');
    const products = JSON.parse(raw);

    res.render('produse.ejs', { products: products });
})

const data = [];
app.post('/', (req, res) => {
    const form = new formidable.IncomingForm({
        uploadDir: path.join(__dirname, 'poze'),
    });

    form.parse(req, (err, fields, files) => {
        if (err) {
            console.log(err);
        }

        const product = {
            produs: fields.nume,
            pret: fields.pret,
            cantitate: fields.cantitate,
            poza: path.join('/poze', files.poza[0].originalFilename),
        };

        data.push(product);

        fs.writeFile('produse.json', JSON.stringify(data, null, 2), (err) => {
            if (err) {
                console.log(err);
            }

            const newPath = path.join(__dirname, 'poze', files.poza[0].originalFilename);
            fs.copyFile(files.poza[0].filepath, newPath, (err) => {
                if (err) {
                    console.log(err);
                }
                else {
                    fs.unlink(files.poza[0].filepath, (err) => {
                        if (err) console.log(err);
                    });
                    console.log("File copied");
                    res.sendFile(__dirname + '/html/comanda.html');
                }
            });
        });
    });
});

app.listen(3000, () => console.log('running'));
const express = require('express');

const app = express();

app.use(express.static('exemple-curs7'));
app.use(express.static('exemple-curs8'));

app.listen(8020, function() {console.log('serverul asculta pe portul 8020')});

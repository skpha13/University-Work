var carti = [
    {
        "titlu":"Matilda",
        "pagini":256
    },
    {
        "titlu":"Little Women",
        "pagini":569
    },
    {
        "titlu":"Hobbit",
        "pagini":300
    },
    {
        "titlu":"Mandrie si prejudecata",
        "pagini":450
    },
    {
        "titlu":"Muntele vrajit",
        "pagini":150
    }
]

function bookPages() {
    var x = parseInt(prompt("Enter number:"));

    var vector = [];
    carti.forEach(carte => {
        if(carte.pagini >= x)
            vector.push(carte.titlu);
    });
}

function citate() {
    var quotes = [
        "Viața este ca mersul pe bicicletă. Pentru a-ți menține echilibrul trebuie să continui să mergi înainte",
        "Nimic nu este permanent în această lume nebună. Nici măcar necazurile noastre",
        "Eșecul este doar oportunitatea de a lua totul de la capăt, de data aceasta, într-un mod mai inteligent",
        "Fă ce trebuie să faci până poți face ceea ce vrei să faci",
        "Nu te lăsa împins de probleme. Lasă-te condus de vise"
    ]

    var item = quotes[Math.floor(Math.random()*quotes.length)];

    document.getElementsByTagName("q")[0].innerText = item;
}

citate();
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

function nume() {
    var name = prompt("Enter name:");
    name = name.toUpperCase();

    var item = document.getElementById("home").firstElementChild;
    item.innerText = "Bine ati venit " + name + "!";
}

function images() {
    var container = document.getElementById("galerie");
    var images = container.getElementsByTagName("img");

    for (let index = 0; index < images.length; index++) {
        images[index].src = "https://cdn4.libris.ro/img/pozeprod/59/1002/D5/25875927.jpg";
        images[index].alt = "carte interesanta";
    }
}

function paragrafe() {
    var para = document.getElementsByTagName("p");


    for(let index = 0; index < para.length; index ++) {
        para[index].innerText = para[index].innerText.toUpperCase();
    }
}

function adauga(info) {
    var art = document.getElementsByTagName("article");

    for (let index = 0; index < art.length; index++) {
        para = document.createElement("p");
        para.innerText = info;
        art[index].appendChild(para);
    }

}

function parcurgere() {
    var items = document.querySelectorAll('figcaption');
    for (let index = 0; index < items.length; index++) {
        items[index].innerText = "Figura " + index;
    }
}

// citate();
// nume();
// images();
// paragrafe();
// parcurgere();
adauga("TEST");



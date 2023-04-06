window.onload = () => {
    const nume = prompt("Introdu nume: ");
    const numar = Math.floor(Math.random() * 20) + 1;

    const mesaj = document.getElementsByClassName("message");
    for(m of mesaj) {
        m.innerText += " " + nume;
    }

    var scor = 20;
    buton = document.getElementById("check");
    buton.addEventListener('click',() => {
        const nrIntrodus = parseInt(document.getElementById("guess").value);
        var temp = "";
        if(nrIntrodus < numar) temp = "mic";
        else temp = "mare";
        if(scor != 1 && nrIntrodus != numar)
        {
            const clas = document.getElementsByClassName("message");
            clas[0].innerText = "Numarul este prea " + temp + ", mai incercati!";
            scor -= 1;
            document.getElementsByClassName("score")[0].innerText = scor.toString();
            document.getElementsByClassName("hightscore")[0].innerText = (20 - scor).toString();

        }
        else if (scor != 1)
        {
            document.getElementsByTagName("body")[0].style.backgroundColor = "red";
            document.getElementsByClassName("message")[0].innerText = "Ai ghicit numarul!";
            document.getElementsByClassName("number")[0].innerText = numar;
            const player = document.getElementById("jucatori");
            const p = document.createElement("p");
            p.innerText += "Jucatorul " + nume + " a castigat jocul cu scorul " + scor;
            player.appendChild(p);
        }
        else
        {
            document.getElementsByClassName("message")[0].innerText = "Ai pierdut jocul!";
            document.getElementById("check").disabled = true;
        }
    });

}
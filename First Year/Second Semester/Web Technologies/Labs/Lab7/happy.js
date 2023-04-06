window.onload = () => {
    const game = document.getElementById("game");
    const pElement = game.querySelector("p");
    pElement.style.visibility = "visible";
    const d = document.getElementById("container");
    for(let i = 0; i < 20; i++)
    {
        const img = document.createElement("img");
        img.src = "sad.png";
        d.appendChild(img);
    }

    const container = document.getElementById("container");
    var scor = 0;
    container.addEventListener('click',(event) => {
        if (event.target.src.indexOf("sad.png") != -1)
        {
            scor += 1;
            console.log(scor);
            document.getElementById("scor").textContent = scor.toString();
            event.target.src = "happy.png";
        }
    });

    setTimeout( function() {
        document.getElementsByTagName("h1")[0].innerText = "Jocul s-a terminat!";
        document.getElementById("container").remove();
    }, 20000);
}
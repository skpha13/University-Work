window.onload = () => {
    var h = document.getElementsByTagName("body")[0];
    for (let i = 0; i < 10; i++) {
        var button = document.createElement("button");
        button.classList.add("copil", "cifra" + i);
        button.textContent = i.toString();
        h.appendChild(button);
    }
    var currentColor = [];
    for(let i=0;i<10;i++)
    {
        let temp = document.getElementsByClassName("cifra"+i)[0];
        currentColor[i] = getComputedStyle(temp).backgroundColor;
    }

    var timeoutID = null;
    document.addEventListener('keydown',function (event)
    {
        var temp = document.getElementsByClassName("cifra" + event.key)[0];
        if (temp)
        {
            temp.style.backgroundColor = "black";
            timeoutID = setTimeout(function () {
                temp.style.backgroundColor = currentColor[event.key];
            }, 1000);
        }
    });

    document.addEventListener('keyup',function (event) {
        var temp = document.getElementsByClassName("cifra" + event.key)[0];
        if(temp)
        {
            clearTimeout(timeoutID);
            temp.style.backgroundColor = currentColor[event.key];
        }
    });
}
window.onload = () => {
    var start = document.getElementById("start");
    var raspuns = document.getElementById("raspuns");
    var intrebare = document.getElementById("intrebare");
    var radio = document.getElementById("form");
    intrebare.style.visibility = "hidden";
    radio.style.visibility = "hidden";
    start.addEventListener('click',function (event) {
       intrebare.style.visibility = "visible";
       radio.style.visibility = "visible";

        var ok = false;
        radio.addEventListener('click',function (event) {
           const selectedOption = document.querySelector('input[name="q1"]:checked');
           if(selectedOption.value === "corect")
           {
               raspuns.textContent = "Raspuns corect";
               ok = true;
           }
           else
           {
               raspuns.textContent = "Raspuns gresit";
               ok = true;
           }
       });
        setTimeout(() => {
            if(ok === false)
                alert("Timpul a expirat");
        }, 5000);
    });
}
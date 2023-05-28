window.onload = () => {
    for(let i=0;i<10;i++)
    {
        var element = document.createElement('div');
        element.classList.add("dreptunghi");
        document.body.appendChild(element);
    }

    var divuri = document.getElementsByClassName('dreptunghi');
    for(let i=0; i<divuri.length;i++) {
        divuri[i].addEventListener('click', (event) => {
            divuri[i].style.height = parseInt(getComputedStyle(divuri[i]).height) + 10 + 'px';
            event.stopPropagation();
        });
    }

    document.addEventListener('click', (event) => {
        for(let i=0;i<divuri.length;i++)
            divuri[i].style.height = '25px';
    });
}
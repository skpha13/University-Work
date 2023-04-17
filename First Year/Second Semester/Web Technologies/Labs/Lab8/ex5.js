window.onload = () => {
    var source = ["img1.jpg","img2.jpg","img3.jpg","img4.jpg","img5.jpg"];

    const items = document.querySelectorAll("#imagini li");
    var index = 0;
    document.getElementById("start").addEventListener('click', function () {
        setInterval( function () {
            const img = document.createElement("img");
            img.src = source[index];

            items[index].textContent = "";
            items[index].appendChild(img);

            (function (i) {
                setTimeout(() => {
                    items[i].textContent = source[i];
                },3000);
            })(index);

            index++;
            if(index === items.length) index = 0;
        },3000);
    });
}
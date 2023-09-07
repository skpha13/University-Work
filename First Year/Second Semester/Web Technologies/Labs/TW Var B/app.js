document.getElementById('form').addEventListener('submit', (event) => {
    event.preventDefault();

    const numbers = document.getElementById('numbers').value;
    const order = document.getElementsByName('order');

    var temp_string = "asc";
    if (order[1].checked) temp_string = "desc";

    document.getElementById('result').textContent = "";

    fetch('/form', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json'
        },
        body: JSON.stringify({ numbers: numbers, order: temp_string })
    })
        .then(response => response.json())
        .then(data => {
            document.getElementById('result').textContent = data.rezultat;
        })
        .catch(error => console.log(error))
});
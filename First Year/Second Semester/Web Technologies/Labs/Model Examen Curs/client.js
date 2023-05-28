document.getElementById('formular').addEventListener('submit', function(event) {
    event.preventDefault();
    const nume = document.getElementById('nume').value;
    fetch('/verifica', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json'
        },
        body: JSON.stringify({ nume: nume })
    })
    .then(response => response.json())
    .then(data => {
        document.getElementById('rezultat').textContent = data.rezultat;
    });
});
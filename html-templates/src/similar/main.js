const jsonInput = `
[
    [
        {
            "description": "Bellecour - Grande roue",
            "id": 1,
            "lat": 45.7574995,
            "long": 4.8313017
        },
        {
            "description": "Rue de la rÃ©publique",
            "id": 3,
            "lat": 45.762994,
            "long": 4.833632
        }
    ],
        [
        {
            "description": "Bellecour - Grande roue",
            "id": 1,
            "lat": 45.7574995,
            "long": 4.8313017
        },
        {
            "description": "Rue de la rÃ©publique",
            "id": 3,
            "lat": 45.762994,
            "long": 4.833632
        }
    ]
]
    `;


const reportDate = 1552141410;


$(document).ready(() => {
    printDate(reportDate);

    const data = JSON.parse(jsonInput);

    console.log(data);

    const container = $("#sensors");
    for (const sensors of data) {
        let rows = '';
        for (const sensor of sensors) {
            rows += `<tr><td>${sensor.id}</td><td>${sensor.long}</td><td>${sensor.lat}</td><td>${sensor.description}</td></tr>`;
        }
        console.log(rows);
        container.append(`<table class="table table-hover table-scroll table-striped"><thead><tr><th>Sensor ID</th><th>Longitude</th><th>Latitude</th><th>Description</th></tr></thead><tbody>${rows}</tbody></table><br>`);
    }

});

function printDate(timestamp) {
    const d = new Date(timestamp * 1000);
    console.log(d);
    $('.report-date').text(d.toLocaleDateString() + " - " + d.toLocaleTimeString());
}

function round(v, d = 5) {
    const mult = 10 ** d;
    console.log(mult);
    return Math.floor(v * mult) / mult
}
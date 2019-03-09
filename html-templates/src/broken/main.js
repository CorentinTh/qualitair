const jsonInput = `
[
    {
        "end": 1550151032,
        "sensor": {
            "description": "PÃ©taouchnok",
            "id": 71,
            "lat": 48.597855,
            "long": 3.401035
        },
        "start": 1550150014
    },
    {
        "end": 1650158000,
        "sensor": {
            "description": "Paris - Tour Eiffel",
            "id": 147,
            "lat": 28.468412,
            "long": 14.351684
        },
        "start": 1550150156
    }
]
    `;


const reportDate = 1552141410;


$(document).ready(() => {
    printDate(reportDate);

    const data = JSON.parse(jsonInput);

    console.log(data);

    const table = $(`#sensors`);

    for (const broken of data) {
        const from = new Date(broken.start * 1000);
        const to = new Date(broken.end * 1000);
        const sensor = broken.sensor || {};

        table.append($(`<tr><td>${from.toLocaleDateString() + ' - ' + from.toLocaleTimeString()}</td><td>${to.toLocaleDateString() + ' - ' + to.toLocaleTimeString()}</td>
<td>${sensor.id}</td><td>${round(sensor.long)}</td><td>${round(sensor.lat)}</td><td>${sensor.description}</td></tr>`));

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
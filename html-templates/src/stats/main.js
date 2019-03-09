const jsonInput = `
{
    "atmo": {
        "1543359600": 2,
        "1543446000": 3,
        "1543532400": 2
    },
    "co2": {
        "avg": 6,
        "deviation": 2.62,
        "max": 10,
        "min": 2
    },
    "o2": {
        "avg": 4.88,
        "deviation": 2.7,
        "max": 10,
        "min": 1
    }
}
    `;


const reportDate = 1552141410;

function addStats(key, stats) {
    $(`#attributes`).append($(`<tr><td><strong>${key}</strong></td><td>${stats.avg}</td><td>${stats.deviation}</td><td>${stats.max}</td><td>${stats.min}</td></tr>`));
}

function addAtmo(stats) {

    for (const timestamp in stats) {
        const value = stats[timestamp];
        const d = new Date(timestamp * 1000);

        $(`#atmo`).append($(`<tr><td>${d.toLocaleDateString()}</td><td>${value}</td></tr>`));

    }


}

$(document).ready(() => {
    printDate(reportDate);

    const data = JSON.parse(jsonInput);

    console.log(data);

    for (const key in data) {
        const stats = data[key];

        if (stats.hasOwnProperty('avg')) {
            addStats(key, stats);
        } else {
            addAtmo(stats);
        }
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
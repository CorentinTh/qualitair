const jsonInput = `
{
    "error": "",
    "lines_inserted": 4201
}
    `;


const reportDate = 1552141410;


$(document).ready(() => {
    printDate(reportDate);

    const data = JSON.parse(jsonInput);

    console.log(data);

    $('#count').text(data.lines_inserted || 0);

    if (data.error && data.error !== "") {
        $('#error').text(data.error);
    }

});

function printDate(timestamp) {
    const d = new Date(timestamp * 1000);
    console.log(d);
    $('.report-date').text(d.toLocaleDateString() + " - " + d.toLocaleTimeString());
}

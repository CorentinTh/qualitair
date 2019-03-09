const jsonInput = `

{
    "pics": [
        [
            [
                {"cO2":0},
                {"cO2":0},
                {"cO2":0},
                {"cO2":1}
            ],            [
                {"cO2":0},
                {"cO2":0},
                {"cO2":0},
                {"cO2":1}
            ],            [
                {"cO2":0},
                {"cO2":0},
                {"cO2":0},
                {"cO2":1}
            ],
            [
                {"cO2":1},
                {"cO2":1},
                {"cO2":1},
                {"cO2":0}
                            ]
        ],
        [
            [
                {"cO2":1},
                {"cO2":1},
                {"cO2":1},
                {"cO2":1}
                           ],            [
                {"cO2":1},
                {"cO2":1},
                {"cO2":1},
                {"cO2":1}
                           ],            [
                {"cO2":1},
                {"cO2":1},
                {"cO2":1},
                {"cO2":1}
                           ],
            [
                {"cO2":0},
                {"cO2":0},
                {"cO2":0},
                {"cO2":1}
            ]
        ]
    ],
    "spatialStep": 2,
    "t0": 1550150155,
    "temporalStep": 1000,
    "x0": 48.8534,
    "y0": 2.3488
}
    `;


const reportDate = 1552141410;

$(document).ready(() => {
    printDate(reportDate);

    const data = JSON.parse(jsonInput);

    console.log(data);

    const gridViewer = $('#grid');

    for (let z = 0; z < data.pics.length; z++) {
        const grid = data.pics[z];
        const realZ = data.t0 + data.temporalStep * z;
        const d = new Date(realZ * 1000);

        const table = $(`<table id="grid-${z}" class="time" style="display: ${z === 0 ? 'table' : 'none'}" cellspacing="0" cellpadding="0"></table>`);
        gridViewer.append(table);

        for (let y = 0; y < grid.length; y++) {
            const row = grid[y];
            const realY = data.y0 + data.spatialStep * y;

            const tr = $('<tr></tr>');
            table.append(tr);

            for (let x = 0; x < row.length; x++) {
                const point = row[x];
                const realX = data.x0 + data.spatialStep * x;
                let isSpike = false;
                let tooltip = 'Longitude: ' + round(realX);
                tooltip += '\nLatitude: ' + round(realY);
                tooltip += '\nDate: ' + d.toLocaleDateString();
                tooltip += '\nTime: ' + d.toLocaleTimeString();

                for (const key in point) {
                    tooltip += '\n' + key;
                    tooltip += ' is spike: ' + (point[key] === 1 ? 'yes' : 'no');

                    if (point[key] === 1) {
                        isSpike = true;
                        $("#rows").append(`<tr><td>${key}</td><td>${d.toLocaleDateString() + ' - ' + d.toLocaleTimeString()}</td><td>${round(realX)}</td><td>${round(realY)}</td></tr>`);
                    }
                }

                const td = $(`<td style="width: ${100 / row.length}%"><div class="tooltip content ${isSpike ? 'spike' : ''}" data-tooltip="${tooltip}" ></div></td>`);
                tr.append(td);

                console.log(point);
            }
        }
    }

    const count = data.pics.length;
    gridViewer.append(`<input id="slider" class="slider" type="range" min="0" max="${count - 1}" value="0" step="1">`);

    $('#slider').on('input', function () {

        const el = $(this);
        const val = el.val();

        gridViewer.find('table').hide();
        $('#grid-' + val).show();
    })
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
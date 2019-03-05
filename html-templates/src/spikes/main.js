
const $ = require('../common/jquery');

const json = `

{
    "pics": [
        [
            [
                {"cO2":1},
                {"cO2":1}
            ],
            [
                {"cO2":1},
                {"cO2":1}
                            ]
        ],
        [
            [
                {"cO2":1},
                {"cO2":1}
                           ],
            [
                {"cO2":1},
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

$(document).ready(() => {

    const data = JSON.parse(json);

    console.log(data);

    const gridViewer  = $('#grid');

    for (let z = 0; z < data.pics.length; z++) {
        const grid = data.pics[z];
        const realZ = data.t0 + data.temporalStep * z;

        // const gridViewerGrid = $('<div></div>');
        // gridViewer.append(gridViewerGrid);

        for (let y = 0; y < grid.length; y++) {
            const row = grid[y];
            const realY = data.y0 + data.spatialStep * y;

            // const gridViewerRow = $('<div></div>');
            // gridViewerGrid.append(gridViewerRow);

            for (let x = 0; x < row.length; x++) {
                const point = row[x];
                const realX = data.x0 + data.spatialStep * x;

                // const gridViewerCell = $('<div></div>');
                // gridViewerRow.append(gridViewerCell);

                for (const key in point){
                    if(point[key] === 1){
                        const d = new Date(realZ * 1000);

                        $("#rows").append(`<tr><td>${key}</td><td>${d.toLocaleDateString() + ' - ' + d.toLocaleTimeString()}</td><td>${realX}</td><td>${realY}</td></tr>`);
                    }
                }

                console.log(point);
            }
        }

    }
});

import * as readline from 'readline';

const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout,
});

// Constants for the Limitations
const LIMITS = {
    X: { min: -30000000, max: 30000000 },
    Y: { min: -319, max: 319 },
    Z: { min: -30000000, max: 30000000 },
};

// Enum for distance methods
enum DistanceMethod {
    EUCLIDEAN = 'euclidean',
    MANHATTAN = 'manhattan',
}

// Function to calculate Euclidean Distance
function calculateEuclideanDistance(coords1: number[], coords2: number[]): number {
    const [x1, y1, z1] = coords1;
    const [x2, y2, z2] = coords2;
    const dx = x1 - x2;
    const dy = y1 - y2;
    const dz = z1 - z2;
    return Math.round(Math.sqrt(dx * dx + dy * dy + dz * dz));
}

// Function to calculate Manhattan Distance
function calculateManhattanDistance(coords1: number[], coords2: number[]): number {
    const [x1, y1, z1] = coords1;
    const [x2, y2, z2] = coords2;
    const dx = Math.abs(x1 - x2);
    const dy = Math.abs(y1 - y2);
    const dz = Math.abs(z1 - z2);
    return dx + dy + dz;
}

function validateCoordinates(coordinates: number[]): boolean {
    return (
        coordinates.length === 3 &&
        coordinates.every((coord) => !isNaN(coord) && validateCoordinateRange(coordinates))
    );
}

// Function to validate coordinate range
function validateCoordinateRange(coords: number[]): boolean {
    return coords.every((coord, index) => {
        const key = Object.keys(LIMITS)[index] as keyof typeof LIMITS;
        return coord >= LIMITS[key].min && coord <= LIMITS[key].max;
    });
}

// Function to prompt for coordinates
async function promptCoordinates(promptText: string): Promise<number[]> {
    return new Promise((resolve, reject) => {
        rl.question(promptText, (input) => {
            const coordinates = input
                .trim()
                .split(' ')
                .map((coord) => parseFloat(coord.trim()));

            if (validateCoordinates(coordinates)) {
                resolve(coordinates);
            } else {
                console.error(`Invalid input. Please enter valid numbers for X (${LIMITS.X.min} - ${LIMITS.X.max}), Y (${LIMITS.Y.min} - ${LIMITS.Y.max}), and Z (${LIMITS.Z.min} - ${LIMITS.Z.max}).`);
                process.exit(1); // Exit the program on invalid input
            }
        });
    });
}


// Function to select a valid distance method
async function selectDistanceMethod(): Promise<DistanceMethod> {
    while (true) {
        const distanceMethod = await new Promise<DistanceMethod>((resolve) => {
            rl.question('Choose the distance method (Euclidean or Manhattan): ', (method) => {
                resolve(method.trim().toLowerCase() as DistanceMethod);
            });
        });

        if (distanceMethod === DistanceMethod.EUCLIDEAN || distanceMethod === DistanceMethod.MANHATTAN) {
            return distanceMethod;
        } else {
            console.error('Invalid distance method. Please choose "Euclidean" or "Manhattan".');
        }
    }
}

async function main() {
    try {
        const coords1 = await promptCoordinates(`Enter the first set of coordinates: `);
        const coords2 = await promptCoordinates(`Enter the second set of coordinates: `);

        const distanceMethod = await selectDistanceMethod();

        let distance: number;

        if (distanceMethod === DistanceMethod.EUCLIDEAN) {
            distance = calculateEuclideanDistance(coords1, coords2);
        } else {
            distance = calculateManhattanDistance(coords1, coords2);
        }

        console.log(`Distance: ${distance}`);
    } finally {
        rl.close();
    }
}

main();

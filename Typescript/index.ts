import * as readline from 'readline';

const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout,
});

const MAX_X = 30000000;
const MIN_X = -30000000;
const MAX_Y = 319; // Maximum build height
const MIN_Y = 0;
const MAX_Z = 30000000;
const MIN_Z = -30000000;

function promptCoordinates(promptText: string, minBounds: number[], maxBounds: number[]): Promise<number[]> {
  return new Promise((resolve, reject) => {
    rl.question(promptText, (input) => {
      const coordinates = input
        .trim()
        .split(' ')
        .map((coord) => parseFloat(coord.trim()));

      if (!validateCoordinates(coordinates, minBounds, maxBounds)) {
        reject(new Error(`Invalid input. Please enter three space-separated numbers within the limits: X (${minBounds[0]} - ${maxBounds[0]}), Y (${minBounds[1]} - ${maxBounds[1]}), Z (${minBounds[2]} - ${maxBounds[2]})`));
      } else {
        resolve(coordinates);
      }
    });
  });
}

function validateCoordinateRange(coord: number, min: number, max: number): boolean {
  return coord >= min && coord <= max;
}

function validateCoordinateInput(coord: number): boolean {
  return !isNaN(coord);
}

function validateCoordinates(coordinates: number[], minBounds: number[], maxBounds: number[]): boolean {
  return (
    coordinates.length === 3 &&
    validateCoordinateInput(coordinates[0]) &&
    validateCoordinateInput(coordinates[1]) &&
    validateCoordinateInput(coordinates[2]) &&
    validateCoordinateRange(coordinates[0], minBounds[0], maxBounds[0]) &&
    validateCoordinateRange(coordinates[1], minBounds[1], maxBounds[1]) &&
    validateCoordinateRange(coordinates[2], minBounds[2], maxBounds[2])
  );
}

// Rest of your code remains the same

async function main() {
  try {
    const coords1 = await promptCoordinates(
      `Enter the first set of coordinates (X ${MIN_X} - ${MAX_X}, Y ${MIN_Y} - ${MAX_Y}, Z ${MIN_Z} - ${MAX_Z}): `,
      [MIN_X, MIN_Y, MIN_Z],
      [MAX_X, MAX_Y, MAX_Z]
    );
    const coords2 = await promptCoordinates(
      `Enter the second set of coordinates (X ${MIN_X} - ${MAX_X}, Y ${MIN_Y} - ${MAX_Y}, Z ${MIN_Z} - ${MAX_Z}): `,
      [MIN_X, MIN_Y, MIN_Z],
      [MAX_X, MAX_Y, MAX_Z]
    );

    const distanceMethod = await new Promise<string>((resolve) => {
      rl.question('Choose the distance method (Euclidean or Manhattan): ', (method) => {
        resolve(method.trim().toLowerCase());
      });
    });

    let distance: number;

    if (distanceMethod === 'euclidean') {
      distance = calculateEuclideanDistance(coords1, coords2);
    } else if (distanceMethod === 'manhattan') {
      distance = calculateManhattanDistance(coords1, coords2);
    } else {
      throw new Error('Invalid distance method. Please choose "Euclidean" or "Manhattan".');
    }

    console.log(`Distance: ${distance.toFixed(2)}`);
  } catch (error) {
    console.error(error.message);
  } finally {
    rl.close();
  }
}

main();
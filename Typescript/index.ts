import * as readline from 'readline';

const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout,
});

const MAX_COORD = 30000000;
const MIN_COORD = -30000000;

function promptCoordinates(promptText: string): Promise<number[]> {
  return new Promise((resolve, reject) => {
    rl.question(promptText, (input) => {
      const coordinates = input
        .trim()
        .split(' ')
        .map((coord) => parseFloat(coord.trim()));

      if (!validateCoordinates(coordinates)) {
        reject(new Error('Invalid input. Please enter three space-separated numbers within the limits.'));
      } else {
        resolve(coordinates);
      }
    });
  });
}

function validateCoordinateRange(coord: number): boolean {
  return coord >= MIN_COORD && coord <= MAX_COORD;
}

function validateCoordinateInput(coord: number): boolean {
  return !isNaN(coord);
}

function validateCoordinates(coordinates: number[]): boolean {
  return (
    coordinates.length === 3 &&
    coordinates.every((coord) => validateCoordinateInput(coord) && validateCoordinateRange(coord))
  );
}

async function main() {
  try {
    const coords1 = await promptCoordinates('Enter the first set of coordinates (x1 y1 z1): ');
    const coords2 = await promptCoordinates('Enter the second set of coordinates (x2 y2 z2): ');

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

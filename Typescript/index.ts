import * as readline from 'readline';

const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout,
});

function promptCoordinates(promptText: string): Promise<number[]> {
  return new Promise((resolve, reject) => {
    rl.question(promptText, (input) => {
      const coordinates = input
        .trim()
        .split(' ')
        .map((coord) => parseFloat(coord.trim()));

      if (coordinates.length !== 3 || coordinates.some(isNaN)) {
        reject(new Error('Invalid input. Please enter three space-separated numbers.'));
      } else {
        resolve(coordinates);
      }
    });
  });
}

function calculateEuclideanDistance(coords1: number[], coords2: number[]): number {
  const dx = coords1[0] - coords2[0];
  const dy = coords1[1] - coords2[1];
  const dz = coords1[2] - coords2[2];
  return Math.round(Math.sqrt(dx * dx + dy * dy + dz * dz));
}

function calculateManhattanDistance(coords1: number[], coords2: number[]): number {
  const dx = Math.abs(coords1[0] - coords2[0]);
  const dy = Math.abs(coords1[1] - coords2[1]);
  const dz = Math.abs(coords1[2] - coords2[2]);
  return dx + dy + dz;
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

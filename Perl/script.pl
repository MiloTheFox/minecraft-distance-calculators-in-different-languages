#!/usr/bin/env perl -T

use strict;
use warnings FATAL => 'all';
use POSIX;
use feature 'say';

# Calculate Euclidean distance between two 3D points
sub euclidean_distance {
    my ($x1, $y1, $z1, $x2, $y2, $z2) = @_;
    my $dx = $x1 - $x2;
    my $dy = $y1 - $y2;
    my $dz = $z1 - $z2;
    my $distance_squared = $dx**2 + $dy**2 + $dz**2;
    return floor($distance_squared);
}

# Calculate Manhattan distance between two 3D points
sub manhattan_distance {
    my ($x1, $y1, $z1, $x2, $y2, $z2) = @_;
    return abs($x1 - $x2) + abs($y1 - $y2) + abs($z1 - $z2);
}

# Main program
sub main {
    # Prompt for the first 3D point
    say "Enter the first 3D point (e.g., '10 32 -54'): ";
    my ($x1, $y1, $z1) = split ' ', <>;

    # Prompt for the second 3D point
    say "Enter the second 3D point (e.g., '5 20 10'): ";
    my ($x2, $y2, $z2) = split ' ', <>;

    # Prompt for the choice of distance calculation
    say "Choose the distance to calculate (euclidean/manhattan): ";
    my $choice = <>;
    chomp($choice);

    my %distance_functions = (
        'euclidean' => \&euclidean_distance,
        'manhattan' => \&manhattan_distance,
    );

    my $distance_function = $distance_functions{lc($choice)};

    if ($distance_function) {
        my $distance = &$distance_function($x1, $y1, $z1, $x2, $y2, $z2);
        say "Distance between the points using '$choice' distance: '$distance'";
    } else {
        die "Invalid choice: '$choice'. Please enter 'euclidean' or 'manhattan'.";
    }
}

main();

package main

import (
	"bufio"
	"fmt"
	"os"
	"slices"
	"strings"
)

type Pair struct {
	x, y int
}

func read_stdin() []string {
	scanner := bufio.NewScanner(os.Stdin)
	scanner.Split(bufio.ScanLines)
	var lines []string
	for scanner.Scan() {
		lines = append(lines, scanner.Text())
	}
	return lines
}

func is_empty_col(col int, lines []string) bool {
	for _, line := range lines {
		if line[col] != '.' {
			return false
		}
	}
	return true
}

func get_empty_cols(lines []string) []int {
	res := []int{}
	for i := 0; i < len(lines[0]); i++ {
		if is_empty_col(i, lines) {
			res = append(res, i)
		}
	}
	return res
}

func load_points(lines []string, weight int) []Pair {
	empty_cols := get_empty_cols(lines)
	pts := []Pair{}
	row := 0
	for _, line := range lines {
		if !strings.Contains(line, "#") {
			row += weight
			continue
		}
		col := 0
		for i := 0; i < len(line); i++ {
			if slices.Contains(empty_cols, i) {
				col += weight
				continue
			}
			if line[i] == '#' {
				pts = append(pts, Pair{row, col})
			}
			col += 1
		}
		row += 1
	}
	return pts
}

func my_abs_diff(x int, y int) int {
	if x < y {
		return y - x
	}
	return x - y
}

func manhattan_distance(a Pair, b Pair) int {
	return my_abs_diff(a.x, b.x) + my_abs_diff(a.y, b.y)
}

func get_distances(pts []Pair) []int {
	dists := []int{}
	for i := 0; i < len(pts); i++ {
		for j := i + 1; j < len(pts); j++ {
			dists = append(dists, manhattan_distance(pts[i], pts[j]))
		}
	}
	return dists
}

func sum(numbers []int) int {
	sum := 0
	for _, num := range numbers {
		sum += num
	}
	return sum
}

func process_lines(lines []string, weight int) int {
	pts := load_points(lines, weight)
	dists := get_distances(pts)
	return sum(dists)
}

func main() {
	fileLines := read_stdin()
	fmt.Println(process_lines(fileLines, 2))
	// fmt.Println(process_lines(fileLines, 10))
	// fmt.Println(process_lines(fileLines, 100))
	fmt.Println(process_lines(fileLines, 1000000))
}

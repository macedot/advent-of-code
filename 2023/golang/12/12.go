package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

const (
	OPERATIONAL = '.'
	DAMAGED     = '#'
	UNKNOWN     = '?'
)

type Elem struct {
	s string
	v []int
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

func sum(numbers []int) int {
	sum := 0
	for _, num := range numbers {
		sum += num
	}
	return sum
}

func parse_values(line string) []int {
	nums := strings.Split(line, ",")
	values := []int{}
	for _, num := range nums {
		v, _ := strconv.Atoi(num)
		values = append(values, v)
	}
	return values
}

func parse_elem(line string) Elem {
	p := strings.Split(line, " ")
	s := p[0]
	v := parse_values(p[1])
	return Elem{s, v}
}

func parse_lines(lines []string) []Elem {
	elements := []Elem{}
	for _, line := range lines {
		elements = append(elements, parse_elem(line))
	}
	return elements
}

func count_arrangement(elem Elem) int {
	return 0
}

func process_elements(elements []Elem) int {
	count := []int{}
	for _, elem := range elements {
		fmt.Println(elem)
		count = append(count, count_arrangement(elem))
	}
	return sum(count)
}

// ???.### 1,1,3
// .??..??...?##. 1,1,3
// ?#?#?#?#?#?#?#? 1,3,1,6
// ????.#...#... 4,1,1
// ????.######..#####. 1,6,5
// ?###???????? 3,2,1

func main() {
	fileLines := read_stdin()
	elements := parse_lines(fileLines)
	fmt.Println(process_elements(elements))
}

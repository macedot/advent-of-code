// https://thepythoncode.com/assistant/code-converter/python/swift/

import Foundation

func timeto(req: Int, cur: Int, prod: Int) -> Int {
    return 1 + max(0, ((req - cur + prod - 1) / prod))
}

func process(blueprint: [Int], mins: Int) -> Int {
    let co = blueprint[1]
    let cc = blueprint[2]
    let cb1 = blueprint[3]
    let cb2 = blueprint[4]
    let cg1 = blueprint[5]
    let cg2 = blueprint[6]
    let mo = max(cc, cb1, cg1)
    var maxx = 0

    func dfs(g: Int, t: Int, o: Int, c: Int, b: Int, ro: Int, rc: Int, rb: Int) {
        let maxg = g + t * t - t
        if t <= 0 || maxg <= maxx {
            return
        }
        maxx = max(maxx, g)
        if rb > 0 {  // create geode robot?
            let dt = max(timeto(req: cg1, cur: o, prod: ro), timeto(req: cg2, cur: b, prod: rb))
            dfs(g: g + max(t - dt, 0), t: t - dt, o: o + dt * ro - cg1, c: c + dt * rc, b: b + dt * rb - cg2, ro: ro, rc: rc, rb: rb)
        }
        if maxg <= maxx {
            return
        }
        if rc > 0 && b + (rb * t) < cg2 * t {  // create obsidian robot?
            let dt = max(timeto(req: cb1, cur: o, prod: ro), timeto(req: cb2, cur: c, prod: rc))
            dfs(g: g, t: t - dt, o: o + dt * ro - cb1, c: c + dt * rc - cb2, b: b + dt * rb, ro: ro, rc: rc, rb: rb + 1)
        }
        if maxg <= maxx {
            return
        }
        if c + (rc * t) < cb2 * t {  // create clay robot?
            let dt = timeto(req: cc, cur: o, prod: ro)
            dfs(g: g, t: t - dt, o: o + dt * ro - cc, c: c + dt * rc, b: b + dt * rb, ro: ro, rc: rc + 1, rb: rb)
        }
        if maxg <= maxx {
            return
        }
        if o + (ro * t) < mo * t {  // create ore robot?
            let dt = timeto(req: co, cur: o, prod: ro)
            dfs(g: g, t: t - dt, o: o + dt * ro - co, c: c + dt * rc, b: b + dt * rb, ro: ro + 1, rc: rc, rb: rb)
        }
    }

    dfs(g: 0, t: mins, o: 0, c: 0, b: 0, ro: 1, rc: 0, rb: 0)
    return maxx
}

func filterString(_ s: String) -> String {
    return s.filter { $0.isWhitespace || $0.isNumber }
}

func parseBlueprint(_ inputString: String) -> [Int] {
    let filteredString = filterString(inputString)
    let components = filteredString.components(separatedBy: CharacterSet.whitespacesAndNewlines)
    let values = components.compactMap { Int($0) }
    return values
}

var values: [[Int]] = []
while let inputString = readLine() {
    let parsedValues = parseBlueprint(inputString)
    values.append(parsedValues)
}


let ans1 = values.map { $0[0] * process(blueprint: $0, mins: 24) }.reduce(0, +)
print(ans1)

let ans2 = values.prefix(3).map { process(blueprint: $0, mins: 32) }.reduce(1, *)
print(ans2)

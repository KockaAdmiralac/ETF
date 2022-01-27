var oldData = `...`.split('\n').map(l => l.split(';'));
var newData = `...`.split('\n').map(l => l.split(';'));
var allStudents = [];
oldData.forEach(s => {
    if (!allStudents.includes(s[1])) {
        allStudents.push(s[1]);
    }
});
newData.forEach(s => {
    if (!allStudents.includes(s[1])) {
        allStudents.push(s[1]);
    }
});
console.log(allStudents.map(function(index) {
    const oldStudent = oldData.find(d => d[1] === index);
    const newStudent = newData.find(d => d[1] === index) || ['999', index, oldStudent[2], '0.00'];
    return `"${index}","${oldStudent[2]}","${oldStudent[0]}","${newStudent[0]}","${oldStudent[3]}","${newStudent[3]}"`;
}).join('\n'));

// (\d+)\. (\d+/\d+) ([^ ]+ [^ ]+) (\d+\.\d+) .*
// $1;$2;$3;$4

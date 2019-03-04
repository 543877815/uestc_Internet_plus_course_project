//
//import com.sun.xml.internal.bind.v2.schemagen.xmlschema.Union;
//import net.sf.jsqlparser.expression.*;
//import net.sf.jsqlparser.expression.operators.arithmetic.*;
//import net.sf.jsqlparser.expression.operators.conditional.AndExpression;
//import net.sf.jsqlparser.expression.operators.conditional.OrExpression;
//import net.sf.jsqlparser.expression.operators.relational.*;
//import net.sf.jsqlparser.schema.Column;
//import net.sf.jsqlparser.schema.Table;
//import net.sf.jsqlparser.statement.select.*;
//
//import java.util.ArrayList;
//import java.util.Iterator;
//import java.util.List;
//
//public class TablesNamesFinder implements SelectVisitor, FromItemVisitor, JoinVisitor, ExpressionVisitor, ItemsListVisitor {
//    private List tables;
//
//    public List getTableList(Select select) {
//        tables = new ArrayList();
//        select.getSelectBody().accept(this);
//        return tables;
//    }
//
//    public void visit(PlainSelect plainSelect) {
//        plainSelect.getFromItem().accept(this);
//
//        if (plainSelect.getJoins() != null) {
//            for (Iterator joinsIt = plainSelect.getJoins().iterator(); joinsIt.hasNext();) {
//                Join join = (Join) joinsIt.next();
//                join.getRightItem().accept(this);
//            }
//        }
//        if (plainSelect.getWhere() != null)
//            plainSelect.getWhere().accept(this);
//
//    }
//
//    public void visit(SetOperationList setOperationList) {
//
//    }
//
//    public void visit(WithItem withItem) {
//
//    }
//
//    public void visit(Union union) {
//        for (Iterator iter = union.getPlainSelects().iterator(); iter.hasNext();) {
//            PlainSelect plainSelect = (PlainSelect) iter.next();
//            visit(plainSelect);
//        }
//    }
//
//    public void visit(Table tableName) {
//        String tableWholeName = tableName.getWholeTableName();
//        tables.add(tableWholeName);
//    }
//
//    public void visit(SubSelect subSelect) {
//
//    }
//
//    public void visit(SubSelect subSelect) {
//        subSelect.getSelectBody().accept(this);
//    }
//
//    public void visit(Addition addition) {
//        visitBinaryExpression(addition);
//    }
//
//    public void visit(Division division) {
//
//    }
//
//    public void visit(Multiplication multiplication) {
//
//    }
//
//    public void visit(Subtraction subtraction) {
//
//    }
//
//    public void visit(AndExpression andExpression) {
//
//    }
//
//    public void visit(OrExpression orExpression) {
//
//    }
//
//    public void visit(Between between) {
//
//    }
//
//    public void visit(EqualsTo equalsTo) {
//
//    }
//
//    public void visit(GreaterThan greaterThan) {
//
//    }
//
//    public void visit(GreaterThanEquals greaterThanEquals) {
//
//    }
//
//    public void visit(AndExpression andExpression) {
//        visitBinaryExpression(andExpression);
//    }
//
//    public void visit(Between between) {
//        between.getLeftExpression().accept(this);
//        between.getBetweenExpressionStart().accept(this);
//        between.getBetweenExpressionEnd().accept(this);
//    }
//
//    public void visit(Column tableColumn) {
//    }
//
//    public void visit(Division division) {
//        visitBinaryExpression(division);
//    }
//
//    public void visit(DoubleValue doubleValue) {
//    }
//
//    public void visit(EqualsTo equalsTo) {
//        visitBinaryExpression(equalsTo);
//    }
//
//    public void visit(Function function) {
//    }
//
//    public void visit(SignedExpression signedExpression) {
//
//    }
//
//    public void visit(JdbcParameter jdbcParameter) {
//
//    }
//
//    public void visit(JdbcNamedParameter jdbcNamedParameter) {
//
//    }
//
//    public void visit(GreaterThan greaterThan) {
//        visitBinaryExpression(greaterThan);
//    }
//
//    public void visit(GreaterThanEquals greaterThanEquals) {
//        visitBinaryExpression(greaterThanEquals);
//    }
//
//    public void visit(InExpression inExpression) {
//        inExpression.getLeftExpression().accept(this);
//        inExpression.getItemsList().accept(this);
//    }
//
//    public void visit(InverseExpression inverseExpression) {
//        inverseExpression.getExpression().accept(this);
//    }
//
//    public void visit(IsNullExpression isNullExpression) {
//    }
//
//    public void visit(JdbcParameter jdbcParameter) {
//    }
//
//    public void visit(LikeExpression likeExpression) {
//        visitBinaryExpression(likeExpression);
//    }
//
//    public void visit(ExistsExpression existsExpression) {
//        existsExpression.getRightExpression().accept(this);
//    }
//
//    public void visit(LongValue longValue) {
//    }
//
//    public void visit(MinorThan minorThan) {
//        visitBinaryExpression(minorThan);
//    }
//
//    public void visit(MinorThanEquals minorThanEquals) {
//        visitBinaryExpression(minorThanEquals);
//    }
//
//    public void visit(Multiplication multiplication) {
//        visitBinaryExpression(multiplication);
//    }
//
//    public void visit(NotEqualsTo notEqualsTo) {
//        visitBinaryExpression(notEqualsTo);
//    }
//
//    public void visit(Column column) {
//
//    }
//
//    public void visit(NullValue nullValue) {
//    }
//
//    public void visit(Function function) {
//
//    }
//
//    public void visit(OrExpression orExpression) {
//        visitBinaryExpression(orExpression);
//    }
//
//    public void visit(Parenthesis parenthesis) {
//        parenthesis.getExpression().accept(this);
//    }
//
//    public void visit(StringValue stringValue) {
//    }
//
//    public void visit(Addition addition) {
//
//    }
//
//    public void visit(Subtraction subtraction) {
//        visitBinaryExpression(subtraction);
//    }
//
//    public void visitBinaryExpression(BinaryExpression binaryExpression) {
//        binaryExpression.getLeftExpression().accept(this);
//        binaryExpression.getRightExpression().accept(this);
//    }
//
//    public void visit(ExpressionList expressionList) {
//        for (Iterator iter = expressionList.getExpressions().iterator(); iter.hasNext();) {
//            Expression expression = (Expression) iter.next();
//            expression.accept(this);
//        }
//
//    }
//
//    public void visit(MultiExpressionList multiExpressionList) {
//
//    }
//
//    public void visit(DateValue dateValue) {
//    }
//
//    public void visit(TimestampValue timestampValue) {
//    }
//
//    public void visit(TimeValue timeValue) {
//    }
//
//    public void visit(CaseExpression caseExpression) {
//    }
//
//    public void visit(WhenClause whenClause) {
//    }
//
//    public void visit(AllComparisonExpression allComparisonExpression) {
//        allComparisonExpression.GetSubSelect().getSelectBody().accept(this);
//    }
//
//    public void visit(AnyComparisonExpression anyComparisonExpression) {
//        anyComparisonExpression.GetSubSelect().getSelectBody().accept(this);
//    }
//
//    public void visit(Concat concat) {
//
//    }
//
//    public void visit(Matches matches) {
//
//    }
//
//    public void visit(BitwiseAnd bitwiseAnd) {
//
//    }
//
//    public void visit(BitwiseOr bitwiseOr) {
//
//    }
//
//    public void visit(BitwiseXor bitwiseXor) {
//
//    }
//
//    public void visit(CastExpression castExpression) {
//
//    }
//
//    public void visit(Modulo modulo) {
//
//    }
//
//    public void visit(AnalyticExpression analyticExpression) {
//
//    }
//
//    public void visit(ExtractExpression extractExpression) {
//
//    }
//
//    public void visit(IntervalExpression intervalExpression) {
//
//    }
//
//    public void visit(OracleHierarchicalExpression oracleHierarchicalExpression) {
//
//    }
//
//    public void visit(RegExpMatchOperator regExpMatchOperator) {
//
//    }
//
//    public void visit(SubJoin subjoin) {
//        subjoin.getLeft().accept(this);
//        subjoin.getJoin().getRightItem().accept(this);
//    }
//
//    public void visit(LateralSubSelect lateralSubSelect) {
//
//    }
//
//    public void visit(ValuesList valuesList) {
//
//    }
//
//    public void visit(NullValue nullValue) {
//
//    }
//
//    public void visit(Table table) {
//
//    }
//}
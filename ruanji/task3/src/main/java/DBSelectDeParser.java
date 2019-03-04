import net.sf.jsqlparser.expression.Alias;
import net.sf.jsqlparser.expression.ExpressionVisitor;
import net.sf.jsqlparser.schema.Table;
import net.sf.jsqlparser.statement.select.Pivot;
import net.sf.jsqlparser.util.deparser.SelectDeParser;

public class DBSelectDeParser extends SelectDeParser {

    public DBSelectDeParser(ExpressionVisitor expressionVisitor, StringBuilder buffer){
        super(expressionVisitor, buffer);
    }

    @Override
    public void visit(Table tableName) {
        String schema = tableName.getSchemaName();
        String table = tableName.getName();

//        if (fullTableName ==null){
//            throw new SqlvpException("table is null");
//        }
        tableName.setSchemaName("user");
        tableName.setName("age");
        StringBuilder buffer = getBuffer();

        buffer.append(tableName.getFullyQualifiedName());
        Pivot pivot = tableName.getPivot();
        if (pivot != null) {
            pivot.accept(this);
        }
        Alias alias = tableName.getAlias();
        if (alias != null) {
            buffer.append(alias);
        }
    }
}
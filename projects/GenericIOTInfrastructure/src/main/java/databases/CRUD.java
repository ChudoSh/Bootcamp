package databases;

public interface CRUD {
    void create(Recordable toCreate);

    Recordable read(Recordable toRead);

    void update(Recordable toUpdate);

    void delete(Recordable toDelete);
}
